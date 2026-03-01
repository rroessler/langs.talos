/// Package Modules
import { Context } from '../../context';
import { Task } from '../../task';

/** Ensures Common Pre-requisites. */
export class Guards extends Task {
    //  PUBLIC METHODS  //

    /**
     * Sets up the current pre-requisites sequence.
     * @param context               Release context.
     */
    override async setup(context: Context.Readonly) {
        context.spinner.start('Fetching Remote...');
    }

    /**
     * Handles ensuring varying conditions.
     * @param context               Release context.
     */
    override async execute(context: Context.Readonly) {
        // pre-fetch certain items now
        await context.git.fetch('--all');

        // check if the current tag exists currently
        const current = context.version.tag;
        const tags = await context.git.tags();
        const exists = tags.all.includes(current);

        // we check for the expected tag now
        context.assert.ok(!exists, `Tag '${current}' already released`);
    }

    /**
     * Tears down the current pre-requisites sequence.
     * @param context               Release context.
     */
    override async teardown(context: Context.Readonly) {
        context.spinner.succeed('Passed Requirements');
    }
}
