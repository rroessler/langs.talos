/// Vendor Modules
import { CodeBlock, type CodeBlockProps } from 'fumadocs-ui/components/codeblock';

/** Expose the Client Code-Block. */
export type Client = Omit<CodeBlockProps, 'Actions'> & { actions?: CodeBlockProps['Actions'] };
export function Client({ actions, ...props }: Client) {
    return <CodeBlock {...props} Actions={actions} />;
}
