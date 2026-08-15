/// VSC Modules
import { Dependency, Disposable } from '@/vscode/utilities';

/// Package Modules
import { Context } from './context';

/** Extension Service Interface. */
export const Service = Dependency.Name('extension.service');
export interface Service extends Disposable {
    context(): Context;
    activate(): Promise<void>;
}
